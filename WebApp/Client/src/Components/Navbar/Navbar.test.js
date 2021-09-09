import React from "react";
import {  shallow } from "enzyme";
import { Navbar } from "./Navbar";

describe("NavBar", () => {
  it("should render initial layout", () => {
    const component = shallow(<Navbar />);
    expect(component.getElements()).toMatchSnapshot();
  });

  it("should render first logo", () => {
    const component = shallow(<Navbar />);
    const img = component.find(".navbar-logo-other");
    expect(img.length).toBe(1);
  });

  it("should render second logo", () => {
    const component = shallow(<Navbar />);
    const img = component.find(".navbar-logo-mobile");
    expect(img.length).toBe(1);
  });
});
